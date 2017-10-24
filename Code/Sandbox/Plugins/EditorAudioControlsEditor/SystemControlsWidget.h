// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <QWidget>
#include <SystemTypes.h>
#include <CryAudio/IAudioInterfacesCommonData.h>

class QAction;
class QHBoxLayout;
class QVBoxLayout;
class QToolButton;
class QSearchBox;
class QAbstractItemModel;
class CMountingProxyModel;

namespace ACE
{
class CSystemAsset;
class CSystemControl;
class CSystemAssetsManager;
class CSystemControlsModel;
class CSystemControlsFilterProxyModel;
class CAudioLibraryModel;
class CAudioTreeView;

class CSystemControlsWidget final : public QWidget
{
	Q_OBJECT

public:

	CSystemControlsWidget(CSystemAssetsManager* pAssetsManager);
	virtual ~CSystemControlsWidget() override;

	bool                         IsEditing() const;
	std::vector<CSystemControl*> GetSelectedControls() const;
	void                         SelectConnectedSystemControl(CSystemControl const* const pControl);
	void                         Reload();
	void                         BackupTreeViewStates();
	void                         RestoreTreeViewStates();

signals:

	void SelectedControlChanged();
	void StartTextFiltering();
	void StopTextFiltering();

private slots:

	void DeleteSelectedControl();
	void OnContextMenu(QPoint const& pos);
	void UpdateCreateButtons();

	void ExecuteControl();
	void StopControlExecution();

private:

	// QObject
	virtual bool eventFilter(QObject* pObject, QEvent* pEvent) override;
	// ~QObject

	void InitAddControlWidget(QHBoxLayout* const pLayout);
	void InitFilterWidgets(QVBoxLayout* const pMainLayout);
	void InitTypeFilters();
	void ResetFilters();
	void ShowControlType(ESystemItemType const type, bool const isVisible);
	void SelectNewAsset(QModelIndex const& parent, int const row);

	CSystemControl*     CreateControl(string const& name, ESystemItemType type, CSystemAsset* const pParent);
	CSystemAsset*       CreateFolder(CSystemAsset* const pParent);
	void                CreateParentFolder();
	bool                IsParentFolderAllowed();

	QAbstractItemModel* CreateLibraryModelFromIndex(QModelIndex const& sourceIndex);
	CSystemAsset*       GetSelectedAsset() const;

	CSystemAssetsManager* const            m_pAssetsManager;
	QSearchBox* const                      m_pSearchBox;
	QToolButton* const                     m_pFilterButton;
	CAudioTreeView* const                  m_pTreeView;
	CSystemControlsModel* const            m_pAssetsModel;
	CSystemControlsFilterProxyModel* const m_pFilterProxyModel;
	CMountingProxyModel*                   m_pMountingProxyModel;
	std::vector<CAudioLibraryModel*>       m_libraryModels;

	QString                                m_filter;
	QWidget*                               m_pFilterWidget;
	QAction*                               m_pCreateParentFolderAction;
	QAction*                               m_pCreateFolderAction;
	QAction*                               m_pCreateTriggerAction;
	QAction*                               m_pCreateParameterAction;
	QAction*                               m_pCreateSwitchAction;
	QAction*                               m_pCreateStateAction;
	QAction*                               m_pCreateEnvironmentAction;
	QAction*                               m_pCreatePreloadAction;

	bool                                   m_isReloading = false;
	bool                                   m_isCreatedFromMenu = false;
};
} // namespace ACE